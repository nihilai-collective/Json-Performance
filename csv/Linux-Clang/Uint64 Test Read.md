
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2823.74 | 0.0361514 | 134.655ms | 3873 | 160 | 35.7779 | 1308.04 | 0.329338 | 0.858385 | 1(Win) | true |
| Glaze | 1347.36 | 0.0489064 | 282.227ms | 3873 | 80 | 143.796 | 2741.34 | 0.0378322 | 1.81933 | 2(Loss) | true |
| Jsonifier (two-stage) | 838.688 | 0.0201632 | 491.562ms | 3873 | 160 | 126.164 | 4404 | 0.44139 | 2.93358 | 3(Loss) | true |
| simdjson (ondemand) | 606.383 | 0.0604212 | 614.836ms | 3873 | 30 | 406.351 | 6091.17 | 0.218963 | 4.06414 | 4(Loss) | true |
