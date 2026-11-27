
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 985.127 | 0.106639 | 1278.15ms | 4630 | 640 | 14621.4 | 4482.18 | 0.0202846 | 5.18277 | 23.0261 | 4.69698 | 0.00609341 | 2.66604e-05 | 1.34989e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 930.12 | 0.0882927 | 1306.41ms | 4630 | 160 | 2810.96 | 4747.25 | 0.0699915 | 5.48614 | 25.8743 | 5.17084 | 0.00809125 | 5.12959e-05 | 0 | 2(Loss) | true |
| Glaze | 879.992 | 0.0841858 | 1336.66ms | 4630 | 4890 | 87255.2 | 5017.67 | 0.0449272 | 5.78698 | 27.0981 | 5.08553 | 0.00287774 | 5.37528e-05 | 1.76231e-05 | 3(Loss) | true |
| simdjson (ondemand) | 863.224 | 0.0553955 | 1348.27ms | 4630 | 4890 | 39262.1 | 5115.14 | 0.0772711 | 5.90352 | 28.7717 | 4.85205 | 0.00154571 | 5.75512e-05 | 1.34713e-05 | 4(Loss) | true |
