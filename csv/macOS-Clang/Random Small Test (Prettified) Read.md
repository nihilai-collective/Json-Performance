
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1886.82 | 0.0574612 | 417.868ms | 8051 | 80 | 437.397 | 4069.29 | 0.0113643 | 1(Win) | true |
| Jsonifier (two-stage) | 1687.52 | 0.0689163 | 476.3ms | 8051 | 4890 | 48079.1 | 4549.9 | 0.00580121 | 2(Loss) | true |
| Glaze | 1268.5 | 0.0764183 | 633.873ms | 8051 | 160 | 3423.2 | 6052.83 | 0.05548 | 3(Loss) | true |
| simdjson (ondemand) | 1008.13 | 0.075687 | 774.61ms | 8051 | 160 | 5316.59 | 7616.14 | 0.0679118 | 4(Loss) | true |
