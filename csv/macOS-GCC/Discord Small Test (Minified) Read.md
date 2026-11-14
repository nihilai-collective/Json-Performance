
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1496.7 | 0.613006 | 302.786ms | 4857 | 640 | 230342 | 3094.8 | 0.373423 | 1(Win) | true |
| Jsonifier (two-stage) | 1261.57 | 0.66195 | 389.431ms | 4857 | 640 | 378043 | 3671.6 | 1.02437 | 2(Loss) | true |
| Glaze | 1183.4 | 0.203031 | 390.387ms | 4857 | 4890 | 308819 | 3914.13 | 0.713515 | 3(Loss) | true |
| simdjson (reflection) | 997.931 | 0.39696 | 479.4ms | 4857 | 2560 | 869099 | 4641.6 | 0.527196 | 4(Loss) | true |
| simdjson (ondemand) | 887.628 | 0.898424 | 563.728ms | 4857 | 320 | 703376 | 5218.4 | 0.229428 | 5(Loss) | true |
