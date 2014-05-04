#ifndef GUI_H
#define GUI_H


/* list of possible focuses in the application */
enum gui_focus {
    GUI_FOCUS_MAIN_MENU,
    GUI_FOCUS_OPTIONS_MENU,
    GUI_FOCUS_GAME,
    GUI_FOCUS_QUIT_CONFIRM
};


/* list of possible errors incurred during GUI handling */
enum gui_error {
    GUI_ERR_OK = 0
};


/* structure used to tell renderer what's going on in the GUI */
struct gui_state {
    enum gui_focus focus;
    enum gui_error error;
};


/* gui_default_state(struct gui_state *state)
 *
 * Description:
 * Fills gui_state structure pointed to by state with initialisation values
 * (basically defaults). Behaviour is undefined if state is NULL.
 *
 * Returns:
 * 0, always.
 */
int gui_default_state(struct gui_state *gstate);


/* gui_render
 *
 * Description:
 * Uses curses to render the GUI according to the gui_state structure pointed to
 * by state. Behaviour is undefined if state is NULL.
 *
 * Returns:
 * 0 upon success, -1 upon error. The error field of *state will be filled with
 * an interpretable error value.
 */
int gui_render(struct gui_state *gstate);


#endif
