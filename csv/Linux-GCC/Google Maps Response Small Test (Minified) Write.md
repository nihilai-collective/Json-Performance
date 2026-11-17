
----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13268.6 | 0.0368953 | 759.666ms | 4390 | 1280 | 17.3471 | 315.528 | 0.121472 | 0.430398 | 1.74146 | 0.277677 | 0.00022779 | 1.833e-05 | 3.91515e-06 | 1(Win) | true |
| simdjson (reflection) | 7999.1 | 0.184025 | 782.663ms | 4390 | 80 | 74.215 | 523.388 | 0.145474 | 0.681916 | 2.52346 | 0.390888 | 0.00022779 | 1.99317e-05 | 0 | 2(Loss) | true |
| Glaze | 3382.78 | 0.155631 | 861.722ms | 4390 | 4890 | 18141.8 | 1237.63 | 0.283494 | 1.52943 | 4.77472 | 0.753987 | 0.000296733 | 4.02476e-05 | 1.0388e-05 | 3(Loss) | true |
