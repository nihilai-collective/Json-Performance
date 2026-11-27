
----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 488.807 | 0.0983878 | 6173.12ms | 2090234 | 30 | 4.82968e+08 | 4.0781e+06 | 1.03397 | 1(Win) | true |
| simdjson (ondemand) | 470.084 | 0.511984 | 6424.22ms | 2090234 | 40 | 1.88544e+10 | 4.24052e+06 | 0.736157 | 2(Loss) | true |
