
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2699.06 | 0.179603 | 141.028ms | 3808 | 40 | 233.59 | 1345.5 | 0.0643708 | 0.89851 | 1(Win) | true |
| simdjson (reflection) | 2675.69 | 0.0518901 | 150.805ms | 3808 | 320 | 158.724 | 1357.26 | 0.0423469 | 0.906744 | 2(Loss) | true |
| Glaze | 2390.17 | 0.0529784 | 164.285ms | 3808 | 80 | 51.8353 | 1519.39 | 0.155732 | 1.01823 | 3(Loss) | true |
| Jsonifier | 2220.85 | 0.11916 | 171.487ms | 3808 | 40 | 151.871 | 1635.22 | 0.116566 | 1.09634 | 4(Loss) | true |
| simdjson (ondemand) | 1514.3 | 0.115515 | 257.455ms | 3808 | 80 | 613.959 | 2398.2 | 0.21636 | 1.61696 | 5(Loss) | true |
