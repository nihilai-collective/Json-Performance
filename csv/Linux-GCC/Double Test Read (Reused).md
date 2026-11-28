
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1466.44 | 0.0740801 | 116.212ms | 1811 | 40 | 30.4487 | 1177.75 | 0.0297089 | 1.64989 | 1(Win) | true |
| Glaze | 1118.98 | 0.0494113 | 158.493ms | 1811 | 80 | 46.5302 | 1543.46 | 0.0267328 | 2.17497 | 2(Loss) | true |
| simdjson (ondemand) | 422.791 | 0.634015 | 416.724ms | 1811 | 320 | 214652 | 4085.01 | 0.0422454 | 5.81971 | 3(Loss) | true |
| simdjson (reflection) | 401.988 | 0.1497 | 435.755ms | 1811 | 2560 | 105900 | 4296.41 | 0.0256053 | 6.12221 | 4(Loss) | true |
