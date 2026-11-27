
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3405.75 | 0.0893664 | 270.702ms | 8051 | 30 | 121.771 | 2254.43 | 0.0266071 | 0.719165 | 1(Win) | true |
| Jsonifier (two-stage) | 3019.8 | 0.0864298 | 301.271ms | 8051 | 30 | 144.875 | 2542.57 | 0.352724 | 0.810997 | 2(Loss) | true |
| Glaze | 2026.38 | 0.178671 | 426.967ms | 8051 | 4890 | 224118 | 3789.04 | 0.0540051 | 1.21354 | 3(Loss) | true |
| simdjson (ondemand) | 1545.98 | 0.184038 | 554.208ms | 8051 | 40 | 3341.69 | 4966.45 | 0.0110755 | 1.59313 | 4(Loss) | true |
