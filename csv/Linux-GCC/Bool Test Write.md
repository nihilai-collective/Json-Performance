
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1983.63 | 0.0909565 | 46.8381ms | 905 | 160 | 25.0591 | 435.1 | 0.0459876 | 1.1718 | 1(Win) | true |
| simdjson (reflection) | 253.587 | 0.031712 | 350.047ms | 905 | 30 | 34.9471 | 3403.47 | 0.0782901 | 9.68641 | 2(Loss) | true |
| Glaze | 193.691 | 0.227914 | 448.835ms | 905 | 1280 | 132017 | 4455.94 | 0.101062 | 12.7031 | 3(Loss) | true |
