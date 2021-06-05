#include "signatures_of_graphs.h"

int main()
{
	//read graph from a file. There is also an option to send it as a 
	std::pair< unsigned short int , std::vector< std::vector<unsigned short int> > > graph = read_graph_from_file( "graph2" ); 
	
	unsigned cap_on_path_length = 30;
	std::vector< std::vector<unsigned short int> > all_paths = compute_paths_in_graph( graph.first , graph.second , cap_on_path_length );
	std::vector< unsigned > path_signature = compute_path_signatures( all_paths );
	std::vector< std::vector< std::vector< unsigned short int > > > gr_paths = compute_graded_paths( all_paths );	
	std::vector< std::vector< poset_element_incidence > > poset = create_poset( gr_paths );
	std::vector< std::vector<size_t> > ms = maximal_simplices_in_poset( poset );
	return 0;
}


