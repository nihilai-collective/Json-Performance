
----
### Marine IK Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4413.22 | 0.652066 | 10448.1ms | 7351818 | 80 | 8.58523e+09 | 1.58869e+06 | 1.37255 | 1(Win) | true |
| simdjson (ondemand) | 3801.45 | 1.2607 | 6053.93ms | 7351818 | 30 | 1.62194e+10 | 1.84436e+06 | 1.49994 | 2(Loss) | true |
