
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3045.92 | 0.243071 | 75.515ms | 2158 | 30 | 80.9195 | 675.667 | 0.15762 | 0.77941 | 1(Win) | true |
| Glaze | 2574.98 | 0.0483703 | 87.3038ms | 2158 | 320 | 47.8259 | 799.241 | 0.0504131 | 0.930539 | 2(Loss) | true |
| simdjson (reflection) | 2534.67 | 0.205782 | 87.3688ms | 2158 | 80 | 223.339 | 811.95 | 0.490226 | 0.944972 | 3(Loss) | true |
| Jsonifier (two-stage) | 2355.87 | 0.173116 | 94.034ms | 2158 | 40 | 91.4814 | 873.575 | 0.124809 | 1.02069 | 4(Loss) | true |
| simdjson (ondemand) | 1883.28 | 0.209476 | 121.443ms | 2158 | 80 | 419.207 | 1092.79 | 0.292539 | 1.28307 | 5(Loss) | true |
