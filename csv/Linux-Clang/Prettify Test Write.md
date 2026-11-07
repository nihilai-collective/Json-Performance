
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6007.63 | 0.302783 | 5733.38ms | 699405 | 40 | 4.52036e+06 | 111026 | 0.127622 | 0.412007 | 1(Win) | true |
| Glaze | 3810.04 | 0.0618667 | 9003.47ms | 699405 | 2560 | 3.00297e+07 | 175065 | 0.144934 | 0.649687 | 2(Loss) | true |
| simdjson (ondemand) | 2407.57 | 0.088831 | 7575.71ms | 767297 | 1280 | 9.33057e+07 | 303938 | 0.0601213 | 1.02819 | 3(Loss) | true |
