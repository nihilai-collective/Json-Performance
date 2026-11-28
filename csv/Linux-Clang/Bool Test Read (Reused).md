
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1711.71 | 0.456286 | 52.1215ms | 905 | 160 | 846.902 | 504.219 | 0.201638 | 1.36527 | 1(Win) | true |
| Glaze | 1390.71 | 0.376001 | 67.2337ms | 905 | 30 | 163.352 | 620.6 | 0.323311 | 1.70162 | 2(Loss) | true |
| simdjson (ondemand) | 443.387 | 0.0469464 | 200.72ms | 905 | 80 | 66.8076 | 1946.55 | 0.526356 | 5.50985 | 3(Loss) | true |
