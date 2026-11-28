
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1836.07 | 0.0635067 | 222.765ms | 4215 | 80 | 154.648 | 2189.31 | 0.171563 | 1.33287 | 1(Win) | true |
| simdjson (reflection) | 1573.35 | 0.0925373 | 262.422ms | 4215 | 80 | 447.164 | 2554.89 | 0.214324 | 1.55842 | 2(Loss) | true |
| Glaze | 1012.57 | 0.195056 | 401.317ms | 4215 | 4890 | 293207 | 3969.85 | 0.299228 | 2.42935 | 3(Loss) | true |
