
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 19720.9 | 0.154625 | 2272.74ms | 466906 | 4890 | 5.96034e+06 | 22578.9 | 0.337908 | 0.125378 | 1(Win) | true |
| simdjson (stage-1) | 17731 | 0.201229 | 2525.88ms | 466906 | 2560 | 6.53756e+06 | 25112.9 | 0.00964302 | 0.139444 | 2(Loss) | true |
