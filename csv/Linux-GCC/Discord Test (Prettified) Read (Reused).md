
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2835.81 | 0.0514612 | 3194.79ms | 83958 | 4890 | 1.03238e+06 | 28234.8 | 0.0934343 | 0.872168 | 1(Win) | true |
| simdjson (reflection) | 2696.17 | 0.0681333 | 3333.19ms | 83958 | 2560 | 1.04807e+06 | 29697.2 | 0.0345347 | 0.917436 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 2366.54 | 0.323497 | 3699.45ms | 83958 | 320 | 3.83344e+06 | 33833.7 | 0.236629 | 1.04536 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2365.8 | 0.138025 | 3736.88ms | 83958 | 1280 | 2.79314e+06 | 33844.2 | 0.134439 | 1.04568 | 3(Tie) | true |
| Glaze | 2254.97 | 0.0840308 | 3920.18ms | 83958 | 2560 | 2.27908e+06 | 35507.6 | 0.243621 | 1.09711 | 5(Loss) | true |
