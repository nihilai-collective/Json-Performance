
----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 203.853 | 0.0912606 | 2165.39ms | 4604 | 1280 | 494555 | 21538.7 | 0.0250214 | 14.8953 | 1(Win) | true |
| simdjson (ondemand) | 160.597 | 0.279016 | 2705.49ms | 4604 | 2560 | 1.48968e+07 | 27340 | 0.252671 | 18.9105 | 2(Loss) | true |
