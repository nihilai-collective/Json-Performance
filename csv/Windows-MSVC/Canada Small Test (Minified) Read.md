
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 529.108 | 0.164388 | 848.023ms | 4630 | 4890 | 920289 | 8345.19 | 0.263274 | 4.66218 | 1(Win) | true |
| Jsonifier (two-stage) | 488.037 | 0.142622 | 926.637ms | 4630 | 40 | 6660.26 | 9047.5 | 0.119882 | 5.05173 | 2(Loss) | true |
| Glaze | 164.349 | 0.0939404 | 2732.32ms | 4630 | 4890 | 3.11489e+06 | 26866.7 | 0.899854 | 15.0459 | 3(Loss) | true |
| simdjson (ondemand) | 160.944 | 0.191802 | 2788.15ms | 4630 | 1280 | 3.54431e+06 | 27435.2 | 0.121162 | 15.3658 | 4(Loss) | true |
