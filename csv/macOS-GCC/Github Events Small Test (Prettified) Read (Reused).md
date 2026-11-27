
----
### Github Events Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2303.37 | 0.519847 | 112.666ms | 2158 | 4890 | 105496 | 893.487 | 0.424929 | 1(Win) | true |
| Glaze | 2146.53 | 0.349517 | 119.033ms | 2158 | 4890 | 54912.9 | 958.77 | 0.174458 | 2(Loss) | true |
| Jsonifier (two-stage) | 2014.52 | 0.911193 | 130.082ms | 2158 | 320 | 27728.9 | 1021.6 | 0.551181 | 3(Loss) | true |
| simdjson (ondemand) | 1808.46 | 0.868496 | 132.145ms | 2158 | 1280 | 125034 | 1138 | 0.601132 | 4(Loss) | true |
| simdjson (reflection) | 1664.8 | 0.982831 | 145.372ms | 2158 | 1280 | 188949 | 1236.2 | 0.722775 | 5(Loss) | true |
