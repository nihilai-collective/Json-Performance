
----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14775 | 0.142024 | 35.4701ms | 5094 | 160 | 34.8906 | 328.8 | 0.148047 | 0.154683 | 1(Win) | true |
| simdjson (reflection) | 10918.3 | 0.101293 | 46.7914ms | 5094 | 640 | 130.001 | 444.942 | 0.301154 | 0.213191 | 2(Loss) | true |
| Glaze | 3728.89 | 0.243222 | 132.274ms | 5094 | 160 | 1606.52 | 1302.81 | 0.139798 | 0.651251 | 3(Loss) | true |
