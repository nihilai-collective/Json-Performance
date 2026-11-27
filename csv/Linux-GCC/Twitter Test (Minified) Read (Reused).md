
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2553.63 | 0.486434 | 5154.43ms | 466906 | 30 | 2.15829e+07 | 174370 | 0.179309 | 0.969351 | 1(Win) | true |
| Jsonifier (two-stage) | 2047.35 | 0.229538 | 6540.01ms | 466906 | 80 | 1.99377e+07 | 217489 | 0.440529 | 1.20909 | 2(Loss) | true |
| Glaze | 2037.2 | 0.100318 | 6477.21ms | 466906 | 1280 | 6.15408e+07 | 218573 | 0.05254 | 1.21513 | 3(Loss) | true |
| simdjson (reflection) | 1958.15 | 0.140269 | 6558.17ms | 466906 | 640 | 6.51138e+07 | 227397 | 0.134277 | 1.26415 | 4(Loss) | true |
| simdjson (ondemand) | 1071.98 | 0.178603 | 5399.62ms | 466906 | 80 | 4.40302e+07 | 415376 | 0.126038 | 2.30935 | 5(Loss) | true |
