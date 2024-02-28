#include "Mesh_Simplification.h"
#include "Mesh_Simplification.proto.h"

#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <PRM/PRM_Include.h>
#include <PRM/PRM_TemplateBuilder.h>
#include <GEO/GEO_PrimPoly.h>
#include <GEO/GEO_Primitive.h>
#include <GU/GU_Detail.h>

#include <iostream>
#include <vector>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_count_ratio_stop_predicate.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Bounded_normal_change_placement.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/GarlandHeckbert_policies.h>
#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
#include <CGAL/boost/graph/IO/polygon_mesh_io.h>


typedef CGAL::Simple_cartesian<double>                          Kernel;
typedef Kernel::FT                                              FT;
typedef Kernel::Point_3                                         Point_3;
typedef CGAL::Surface_mesh<Point_3>                             Surface_mesh;
typedef boost::graph_traits<Surface_mesh>::vertex_descriptor	vertex_descriptor;
typedef boost::graph_traits<Surface_mesh>::face_descriptor		face_descriptor;
namespace SMS = CGAL::Surface_mesh_simplification;

typedef SMS::GarlandHeckbert_plane_policies<Surface_mesh, Kernel>                  Classic_plane;
typedef SMS::GarlandHeckbert_probabilistic_plane_policies<Surface_mesh, Kernel>    Prob_plane;
typedef SMS::GarlandHeckbert_triangle_policies<Surface_mesh, Kernel>               Classic_tri;
typedef SMS::GarlandHeckbert_probabilistic_triangle_policies<Surface_mesh, Kernel> Prob_tri;

template <typename GHPolicies>
void collapse_gh(Surface_mesh& mesh,
	const double ratio)
{

	SMS::Edge_count_ratio_stop_predicate<Surface_mesh> stop(ratio);

	// Garland&Heckbert simplification policies

	typedef typename GHPolicies::Get_cost                                        GH_cost;
	typedef typename GHPolicies::Get_placement                                   GH_placement;
	typedef SMS::Bounded_normal_change_placement<GH_placement>                   Bounded_GH_placement;

	GHPolicies gh_policies(mesh);
	const GH_cost& gh_cost = gh_policies.get_cost();
	const GH_placement& gh_placement = gh_policies.get_placement();
	Bounded_GH_placement placement(gh_placement);

	int r = SMS::edge_collapse(mesh, stop,
		CGAL::parameters::get_cost(gh_cost)
		.get_placement(placement));

	std::cout << "\nFinished!\n" << r << " edges removed.\n" << edges(mesh).size() << " final edges.\n";
}


const char* inputlabel[] = { "Input Geometry", 0 };
const UT_StringHolder Mesh_Simplification::theSOPTypeName("Mesh_Simplification");



static const char* theDsFile = R"THEDSFILE(
{
    name	parameters
    parm {
        name    "divs"
        label   "Simplifications"
        type    integer
        default { "0" }
        range   { 0! 100 }
    }
}
)THEDSFILE";


//
PRM_Template* Mesh_Simplification::buildTemplates()
{
	static PRM_TemplateBuilder templ("Mesh_Simplification.cpp", theDsFile);
	return templ.templates();
}

class Mesh_SimplificationVerb : public SOP_NodeVerb
{
public:
	Mesh_SimplificationVerb() {}
	virtual ~Mesh_SimplificationVerb() {}
	virtual SOP_NodeParms* allocParms() const { return new Mesh_SimplificationParms(); }
	virtual UT_StringHolder name() const { return Mesh_Simplification::theSOPTypeName; }
	virtual CookMode cookMode(const SOP_NodeParms* parms) const { return COOK_GENERIC; }
	virtual void cook(const CookParms& cookparms) const;
	/// This static data member automatically registers
	/// this verb class at library load time.
	static const SOP_NodeVerb::Register<Mesh_SimplificationVerb> theVerb;
};

// The static member variable definition has to be outside the class definition.
// The declaration is inside the class.
const SOP_NodeVerb::Register<Mesh_SimplificationVerb> Mesh_SimplificationVerb::theVerb;

const SOP_NodeVerb*
Mesh_Simplification::cookVerb() const
{
	return Mesh_SimplificationVerb::theVerb.get();
}

OP_ERROR Mesh_Simplification::cookMySop(OP_Context& context)
{
	OP_AutoLockInputs inputs(this);
	if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	duplicateSource(0, context);

	// Flag the SOP as being time dependent (i.e. cook on time changes)
	//flags().setTimeDep(true);
	return cookMyselfAsVerb(context);
}

// policy can be "cp" (classic plane), "ct" (classic triangle), "pp" (probabilistic plane), "pt" (probabilistic triangle)
void Mesh_SimplificationVerb::cook(const SOP_NodeVerb::CookParms& cookparms) const
{
	auto&& sopparms = cookparms.parms<Mesh_SimplificationParms>();
	GU_Detail* detail = cookparms.gdh().gdpNC();

	Surface_mesh surface_mesh;
	std::vector<vertex_descriptor> vvd;
	for (GA_Index i = 0; i < detail->getNumPoints(); i++)
	{
		UT_Vector3 utpos = detail->getPos3(detail->pointOffset(i));
		Point_3 p3pos(utpos.x(), utpos.y(), utpos.z());
		vertex_descriptor vd = surface_mesh.add_vertex(p3pos);
		vvd.push_back(vd);
	}

	bool is_triangle = true;
	for (GA_Index i = 0; i < detail->getNumPrimitives(); i++)
	{
		GA_Primitive* prim = detail->getPrimitiveByIndex(i);
		GA_Size n = prim->getVertexCount();
		if (n != 3)
		{
			is_triangle = false;
			break;
		}

		vertex_descriptor v0 = vvd[prim->getPointIndex(0)];
		vertex_descriptor v1 = vvd[prim->getPointIndex(1)];
		vertex_descriptor v2 = vvd[prim->getPointIndex(2)];
		face_descriptor fd = surface_mesh.add_face(v0, v1, v2);

		if (fd == Surface_mesh::null_face())
			fd = surface_mesh.add_face(v0, v2, v1);
	}

	if (!is_triangle)
	{
		std::cout << "not all triangle";
		return;
	}

	std::cout << "Input mesh has " << num_vertices(surface_mesh) << " nv "
		<< num_edges(surface_mesh) << " ne "
		<< num_faces(surface_mesh) << " nf " << std::endl;


	double k = (int32)sopparms.getDivs()*0.01;
	//std::cout << "Collapsing edges of mesh and aiming for " << k << "% of the input edges..." << std::endl;
	const std::string policy = "cp";
	if (policy == "cp")
		collapse_gh<Classic_plane>(surface_mesh, k);
	else if (policy == "ct")
		collapse_gh<Classic_tri>(surface_mesh, k);
	else if (policy == "pp")
		collapse_gh<Prob_plane>(surface_mesh, k);
	else
		collapse_gh<Prob_tri>(surface_mesh, k);


	std::cout << surface_mesh.number_of_edges() << " final edges.\n";


	detail->clearAndDestroy();

	std::map<vertex_descriptor, GA_Offset> mvdoff;
	for (const vertex_descriptor& vd : vertices(surface_mesh))
	{
		GA_Offset ptoff = detail->appendPointOffset();
		Point_3 p3pos = surface_mesh.point(vd);
		UT_Vector3 utpos(p3pos.x(), p3pos.y(), p3pos.z());
		detail->setPos3(ptoff, utpos);
		mvdoff.insert(std::pair<vertex_descriptor, GA_Offset>(vd, ptoff));
	}

	//https://www.coder.work/article/7300500

	for (const face_descriptor& fd : faces(surface_mesh))
	{
		GEO_PrimPoly* poly = (GEO_PrimPoly*)detail->appendPrimitive(GA_PRIMPOLY);
		for (vertex_descriptor vd : vertices_around_face(halfedge(fd, surface_mesh), surface_mesh))
		{
			std::map<vertex_descriptor, GA_Offset>::iterator it = mvdoff.find(vd);
			if (it != mvdoff.end())
			{
				poly->appendVertex(it->second);
			}
		}
		poly->close();
	}
}

class  Mesh_SimplificationOperator : public  OP_Operator
{
public:
	Mesh_SimplificationOperator()
		: OP_Operator(
			Mesh_Simplification::theSOPTypeName,
			"Mesh_Simplification",
			Mesh_Simplification::myConstructor,
			Mesh_Simplification::buildTemplates(),
			1,
			1,
			nullptr,
			0,
			inputlabel)
	{}
	virtual  ~Mesh_SimplificationOperator() {}

	virtual bool getOpHelpURL(UT_String& url)
	{
		url.harden(""); return true;
	}
};

void newSopOperator(OP_OperatorTable* table)
{
	table->addOperator(new Mesh_SimplificationOperator());
}