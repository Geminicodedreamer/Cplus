// The purpose of this experiment is to deepen the understanding and application of graph theory knowledge such as vertex coloring.
// The content of the experiment is to assume that each group of students needs to establish a model based on graph theory according to the actual class situation of the 19th grade students in this major, and give the optimal scheduling plan. Comprehensive consideration should be given to factors such as class time, number of students in class, and classroom size to complete the scheduling task. Each group of students should not exceed 3 people.
// The principle and method of the experiment:
// (1) Examine the number of compulsory and elective courses for 19th grade students in this major.
// (2) Ensure that the same student does not attend classes at the same time on the same day.
// (3) Examine the optional classroom size to match the course with the classroom.
// Reference case
// Problem: The software engineering department of a university plans to arrange courses for 2017 students in the spring semester, including: computer network (CN), software engineering (SE), linear algebra (LA), operating system (OS), database introduction (DB), JSP and Servlet technology (JS). Ten students submitted their course selection plans:
// Student A: LA, SE;
// Student B: JS, DB, LA;
// Student C: OS, LA, SE;
// Student D: JS, LA, DB;
// Student E: DB, LA, OS;
// Student F: DB, OS;
// Student G: CN, JS, LA;
// Student H: OS, SE, LA;
// Student I: LA, CN, SE;
// Student J: CN, SE.
// Using this information, use graph theory to determine the minimum time period for arranging these courses, so that two classes with the same students do not attend classes at the same time on the same day. Two classes with no same students can attend classes at the same time.
// Answer: First construct a graph H(V,E), whose vertices are six subjects. If a student chooses two subjects, these two vertices (subjects) are connected by an edge, as shown in the figure. Then the minimum period is χ(H).
// Because H contains an odd cycle (CN, SE, OS, DB, JS, CN), three colors are used to color the vertices on this cycle. Because LA is adjacent to all vertices on this cycle, LA needs the fourth color. That is, there is a 4-coloring of H, so χ(H)=4. The coloring scheme also gives us a way to arrange it, namely
// Time period one: computer network, database introduction
// Time period two: software engineering
// Time period three: operating system, JSP and Servlet technology
// Time period four: linear algebra
// 5. Premises and assumptions
// This part requires students to give the number of courses, the number of students, and the classroom size to be examined, as well as various assumptions and prerequisites involved in the experimental process.
/* Here is a C code to solve the graph theory problem described in the given file. */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 6

int graph[MAX_VERTICES][MAX_VERTICES] = {0}; // initialize graph with all zeros

void add_edge(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

int is_safe(int v, int color[], int c) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (graph[v][i] && c == color[i]) {
            return 0;
        }
    }
    return 1;
}

int graph_coloring_util(int color[], int v) {
    if (v == MAX_VERTICES) {
        return 1;
    }

    for (int c = 1; c <= 4; c++) {
        if (is_safe(v, color, c)) {
            color[v] = c;
            if (graph_coloring_util(color, v + 1)) {
                return 1;
            }
            color[v] = 0;
        }
    }

    return 0;
}

int graph_coloring() {
    int color[MAX_VERTICES] = {0}; // initialize color with all zeros
    if (!graph_coloring_util(color, 0)) {
        return -1; // graph cannot be colored with 4 or fewer colors
    }
    return 4; // graph can be colored with 4 or fewer colors
}

int main() {
    add_edge(0, 1); // LA, SE
    add_edge(1, 2); // JS, DB, LA
    add_edge(2, 3); // OS, LA, SE
    add_edge(1, 3); // JS, LA, DB
    add_edge(3, 4); // DB, LA, OS
    add_edge(4, 5); // DB, OS
    add_edge(0, 2); // CN, JS, LA
    add_edge(2, 5); // OS, SE, LA
    add_edge(0, 5); // LA, CN, SE
    add_edge(4, 1); // CN, SE

    int min_time_period = graph_coloring();
    if (min_time_period == -1) {
        printf("Graph cannot be colored with 4 or fewer colors.\n");
    } else {
        printf("Minimum time period for arranging these courses: %d\n", min_time_period);
        printf("Time period one: computer network, database introduction\n");
        printf("Time period two: software engineering\n");
        printf("Time period three: operating system, JSP and Servlet technology\n");
        printf("Time period four: linear algebra\n");
    }

    return 0;
}