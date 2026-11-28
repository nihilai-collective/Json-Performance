
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2476.92 | 0.0328764 | 37.6588ms | 905 | 1280 | 16.7978 | 348.447 | 0.0806502 | 0.924298 | 1(Win) | true |
| Jsonifier | 2452.57 | 0.0625579 | 38.654ms | 905 | 320 | 15.5084 | 351.906 | 0.0195403 | 0.93606 | 2(Loss) | true |
| simdjson (reflection) | 1309.67 | 0.152615 | 69.1256ms | 905 | 30 | 30.3448 | 659 | 0 | 1.81845 | 3(Loss) | true |
| simdjson (ondemand) | 507.64 | 0.260235 | 172.479ms | 905 | 4890 | 95724.9 | 1700.17 | 0.0675204 | 4.80329 | 4(Loss) | true |
