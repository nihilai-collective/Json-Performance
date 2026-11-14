
----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 501.617 | 0.0628447 | 5492.08ms | 56369 | 2560 | 1.16122e+07 | 107169 | 0.152345 | 6.05774 | 1(Win) | true |
| simdjson (ondemand) | 170.227 | 0.150817 | 8054.35ms | 56369 | 320 | 7.25896e+07 | 315800 | 0.130891 | 17.8535 | 2(Loss) | true |
