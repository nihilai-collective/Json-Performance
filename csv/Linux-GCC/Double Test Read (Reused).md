
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1466.97 | 0.0389189 | 121.589ms | 1811 | 160 | 33.5918 | 1177.33 | 0.0806263 | 1.64793 | 1(Win) | true |
| Glaze | 1028.33 | 0.0372139 | 173.34ms | 1811 | 160 | 62.5028 | 1679.52 | 0.0234387 | 2.36757 | 2(Loss) | true |
| simdjson (ondemand) | 384.057 | 0.0986413 | 454.281ms | 1811 | 80 | 1574.18 | 4497 | 0.338521 | 6.40697 | 3(Loss) | true |
| simdjson (reflection) | 345.826 | 0.217388 | 506.886ms | 1811 | 1280 | 150870 | 4994.14 | 0.0217959 | 7.12032 | 4(Loss) | true |
