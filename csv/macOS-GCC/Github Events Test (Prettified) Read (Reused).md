
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2369.66 | 0.0813675 | 3268.11ms | 65103 | 2560 | 1.16351e+06 | 26200.8 | 0.132997 | 1(Win) | true |
| Jsonifier (two-stage) | 2157.72 | 0.252445 | 3635.27ms | 65103 | 40 | 211060 | 28774.4 | 0.0592768 | 2(Loss) | true |
| Glaze | 2075.1 | 0.134196 | 3764.51ms | 65103 | 40 | 64485.7 | 29920 | 0.106838 | 3(Loss) | true |
| simdjson (reflection) | 1734.51 | 0.428386 | 5067.69ms | 65103 | 80 | 1.88109e+06 | 35795.2 | 0.30303 | 4(Loss) | true |
| simdjson (ondemand) | 1453.31 | 0.137523 | 5276.97ms | 65103 | 640 | 2.20912e+06 | 42721.2 | 0.0834005 | 5(Loss) | true |
