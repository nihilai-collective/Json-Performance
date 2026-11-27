
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5909.86 | 0.04304 | 5839.24ms | 699405 | 2560 | 6.04069e+06 | 112863 | 0.0889409 | 0.418788 | 1(Win) | true |
| Glaze | 3861.43 | 0.0548178 | 8903.5ms | 699405 | 1280 | 1.14766e+07 | 172735 | 0.0332877 | 0.641051 | 2(Loss) | true |
| simdjson (ondemand) | 2509.97 | 0.0647843 | 7446.35ms | 767297 | 640 | 2.28301e+07 | 291538 | 0.0718911 | 0.986256 | 3(Loss) | true |
