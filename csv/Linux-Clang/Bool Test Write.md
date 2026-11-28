
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2121.29 | 0.134105 | 43.5174ms | 905 | 80 | 23.8163 | 406.863 | 0.0030722 | 1.09052 | 1(Win) | true |
| Glaze | 196.57 | 0.0378807 | 442.231ms | 905 | 30 | 82.9885 | 4390.67 | 0.0394933 | 12.5135 | 2(Loss) | true |
