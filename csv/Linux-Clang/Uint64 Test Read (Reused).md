
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3036.32 | 0.0857871 | 126.574ms | 3873 | 30 | 32.6713 | 1216.47 | 0.248736 | 0.797711 | 1(Win) | true |
| Glaze | 1368.11 | 0.0556719 | 273.041ms | 3873 | 30 | 67.7713 | 2699.77 | 0.212816 | 1.7906 | 2(Loss) | true |
| Jsonifier (two-stage) | 853.06 | 0.064001 | 450.215ms | 3873 | 30 | 230.372 | 4329.8 | 0.0762741 | 2.88417 | 3(Loss) | true |
| simdjson (ondemand) | 618.69 | 0.0405893 | 622.425ms | 3873 | 40 | 234.872 | 5970 | 0.389321 | 3.98207 | 4(Loss) | true |
