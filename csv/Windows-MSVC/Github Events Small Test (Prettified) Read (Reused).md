
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1545.44 | 0.335785 | 157.258ms | 2158 | 4890 | 97775.3 | 1331.68 | 0.1759 | 1.56815 | 1(Win) | true |
| Jsonifier (two-stage) | 1416.28 | 0.23167 | 181.501ms | 2158 | 320 | 3626.57 | 1453.12 | 0.0430293 | 1.71088 | 2(Loss) | true |
| Jsonifier | 1191.56 | 0.278091 | 208.524ms | 2158 | 4890 | 112812 | 1727.18 | 0.923737 | 2.04471 | 3(Loss) | true |
| simdjson (ondemand) | 883.748 | 0.154131 | 251.136ms | 2158 | 160 | 2061.32 | 2328.75 | 0.0536481 | 2.76505 | 4(Loss) | true |
