
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2500.51 | 0.0220374 | 4273.13ms | 83958 | 4890 | 243499 | 32020.9 | 0.0323646 | 2.0595 | 9.17348 | 1.69356 | 0.00416281 | 1.49481e-05 | 7.47282e-06 | 1(Win) | true |
| simdjson (ondemand) | 2248.14 | 0.0484336 | 4600.49ms | 83958 | 640 | 190437 | 35615.4 | 0.101938 | 2.28872 | 9.63681 | 1.58889 | 0.00452401 | 4.71962e-05 | 3.46155e-05 | 2(Loss) | true |
