
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2083.62 | 0.0667244 | 969.812ms | 5094 | 4890 | 11834.7 | 2331.52 | 0.0657081 | 2.46979 | 10.8481 | 2.0905 | 0.00244985 | 3.67327e-05 | 8.35017e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1441.52 | 0.200632 | 1066.68ms | 5094 | 40 | 1828.69 | 3370.07 | 0.115344 | 3.55139 | 15.9358 | 2.66333 | 0.00165881 | 0.00021594 | 0.000147232 | 2(Loss) | true |
| Glaze | 1269.75 | 0.0950281 | 1112.67ms | 5094 | 1280 | 16919.8 | 3825.96 | 0.324724 | 4.02409 | 16.4299 | 3.16608 | 0.00375764 | 5.49053e-05 | 1.34963e-05 | 3(Loss) | true |
| simdjson (ondemand) | 848.596 | 0.0615287 | 1313.67ms | 5094 | 4890 | 60671 | 5724.77 | 0.0465342 | 6.01126 | 22.7517 | 3.80566 | 0.00538141 | 0.000130391 | 6.09001e-05 | 4(Loss) | true |
