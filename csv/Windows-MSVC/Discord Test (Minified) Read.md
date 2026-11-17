
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 868.443 | 0.0338043 | 6194.74ms | 56369 | 4890 | 2.14117e+06 | 61901.2 | 0.0261551 | 3.49827 | 1(Win) | true |
| simdjson (ondemand) | 792.181 | 0.0462075 | 6795.93ms | 56369 | 4890 | 4.80801e+06 | 67860.3 | 0.167005 | 3.8353 | 2(Loss) | true |
