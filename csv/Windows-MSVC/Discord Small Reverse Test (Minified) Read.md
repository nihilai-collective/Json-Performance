
----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 473.68 | 0.210343 | 988.927ms | 4857 | 80 | 33846.5 | 9778.75 | 0.0895599 | 6.40249 | 1(Win) | true |
| simdjson (ondemand) | 179.395 | 0.119616 | 2587.52ms | 4857 | 1280 | 1.22097e+06 | 25820.2 | 0.016947 | 16.9291 | 2(Loss) | true |
