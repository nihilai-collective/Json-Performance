
----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14416.6 | 1.00231 | 401.695ms | 58581 | 80 | 120692 | 3875.2 | 1.42379 | 1(Win) | true |
| simdjson (reflection) | 9198.37 | 1.7294 | 564.388ms | 58581 | 80 | 882621 | 6073.6 | 2.4666 | 2(Loss) | true |
| Glaze | 3308.24 | 0.324077 | 1708.04ms | 58581 | 2560 | 7.66753e+06 | 16887.3 | 2.61297 | 3(Loss) | true |
