
----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 8734.89 | 0.31634 | 5117.74ms | 466906 | 640 | 1.6643e+07 | 50976.7 | 0.089596 | 0.283168 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 8718.73 | 0.10657 | 5089.8ms | 466906 | 2560 | 7.58337e+06 | 51071.2 | 2.1477 | 0.283733 | 1(Tie) | true |
| simdjson (ondemand) | 7569.72 | 0.151509 | 5942.46ms | 466906 | 640 | 5.0834e+06 | 58823.4 | 0.0332834 | 0.326846 | 3(Loss) | true |
| simdjson (reflection) | 7389.58 | 0.13321 | 5940.27ms | 466906 | 1280 | 8.24717e+06 | 60257.3 | 0.0236404 | 0.334802 | 4(Loss) | true |
| Glaze | 3083.34 | 0.323128 | 7390.4ms | 466906 | 40 | 8.71016e+06 | 144414 | 0.328009 | 0.802801 | 5(Loss) | true |
