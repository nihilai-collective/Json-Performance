
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2027.39 | 0.10113 | 354.154ms | 6701 | 40 | 406.471 | 3152.12 | 0.327013 | 1(Win) | true |
| Jsonifier (two-stage) | 1547.23 | 0.171628 | 423.612ms | 6701 | 2560 | 128644 | 4130.34 | 0.0106574 | 2(Loss) | true |
| Glaze | 1264.03 | 1.55709 | 452.396ms | 6701 | 80 | 495772 | 5055.7 | 1.01177 | 3(Loss) | true |
| simdjson (ondemand) | 840.174 | 0.150598 | 833.036ms | 6701 | 40 | 5248.55 | 7606.25 | 2.22282 | 4(Loss) | true |
