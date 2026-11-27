
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1260.49 | 0.696722 | 4275.82ms | 56369 | 4890 | 4.31748e+08 | 42648.2 | 0.140834 | 2.40959 | 1(Win) | true |
| Glaze | 1076.53 | 0.562014 | 5017.54ms | 56369 | 4890 | 3.85152e+08 | 49936.1 | 0.433316 | 2.8214 | 2(Loss) | true |
| Jsonifier (two-stage) | 1012.36 | 0.685792 | 5414.69ms | 56369 | 80 | 1.06092e+07 | 53101.2 | 0.115213 | 3.00091 | 3(Loss) | true |
| simdjson (ondemand) | 768.104 | 0.495193 | 7292.81ms | 56369 | 160 | 1.92181e+07 | 69987.5 | 0.0553364 | 3.95535 | 4(Loss) | true |
