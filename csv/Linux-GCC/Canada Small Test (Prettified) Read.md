
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1917.35 | 0.28149 | 581.814ms | 11579 | 2560 | 672832 | 5759.3 | 0.0609305 | 1.2853 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1904.36 | 0.308125 | 578.48ms | 11579 | 640 | 204304 | 5798.58 | 0.691291 | 1.29399 | 1(Tie) | true |
| simdjson (ondemand) | 1713.23 | 0.0778911 | 673.545ms | 11579 | 40 | 1008.21 | 6445.5 | 0.00930795 | 1.43899 | 3(Loss) | true |
| simdjson (reflection) | 1691.3 | 0.208135 | 658.015ms | 11579 | 2560 | 472753 | 6529.07 | 0.0427538 | 1.45792 | 4(Loss) | true |
| Glaze | 1514.76 | 0.0441761 | 756.745ms | 11579 | 40 | 414.846 | 7289.98 | 0.329961 | 1.629 | 5(Loss) | true |
