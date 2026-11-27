
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 30925.3 | 0.0510452 | 98.6721ms | 31235 | 320 | 77.3599 | 963.225 | 0.122485 | 0.0777845 | 1(Win) | true |
| Glaze | 5945.8 | 0.561923 | 502.326ms | 31235 | 320 | 253611 | 5009.93 | 0.246835 | 0.414118 | 2(Loss) | true |
| simdjson (reflection) | 569.927 | 0.109719 | 5267.45ms | 31235 | 1280 | 4.2094e+06 | 52266.4 | 0.0472982 | 4.34184 | 3(Loss) | true |
