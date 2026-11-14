
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 4314.59 | 0.222633 | 87.899ms | 3808 | 80 | 280.922 | 841.7 | 0.00297027 | 1(Win) | true |
| Jsonifier (two-stage) | 4224.58 | 0.0955706 | 89.7ms | 3808 | 640 | 431.973 | 859.634 | 0.213116 | 2(Loss) | true |
| Jsonifier | 4212.81 | 0.0923614 | 89.7641ms | 3808 | 640 | 405.706 | 862.036 | 0.0208489 | 3(Loss) | true |
| Glaze | 2620.44 | 0.0837626 | 142.188ms | 3808 | 4890 | 6589.52 | 1385.87 | 0.00987684 | 4(Loss) | true |
