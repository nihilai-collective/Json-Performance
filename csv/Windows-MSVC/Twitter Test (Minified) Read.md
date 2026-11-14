
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24946.4 | 0.118876 | 1820.81ms | 466906 | 4890 | 2.2016e+06 | 17849.3 | 0.0328868 | 0.099097 | 1(Win) | true |
| simdjson (stage-1) | 20781.4 | 0.0545067 | 2188.82ms | 466906 | 30 | 4091.95 | 21426.7 | 0.0155545 | 0.118985 | 2(Loss) | true |
