
----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14918.3 | 0.248421 | 378.575ms | 58581 | 4890 | 423214 | 3744.88 | 0.229735 | 1(Win) | true |
| simdjson (reflection) | 10962.5 | 0.268299 | 518.75ms | 58581 | 2560 | 478597 | 5096.2 | 0.379232 | 2(Loss) | true |
| Glaze | 3538 | 0.279789 | 1633.98ms | 58581 | 1280 | 2.49844e+06 | 15790.6 | 0.208549 | 3(Loss) | true |
