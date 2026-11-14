
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1159.18 | 0.0912872 | 5119.26ms | 56369 | 160 | 286761 | 46375.6 | 0.0283095 | 2.62043 | 1(Win) | true |
| simdjson (ondemand) | 1009.66 | 0.0975292 | 5783.27ms | 56369 | 2560 | 6.90301e+06 | 53243.3 | 0.0363763 | 3.00889 | 2(Loss) | true |
