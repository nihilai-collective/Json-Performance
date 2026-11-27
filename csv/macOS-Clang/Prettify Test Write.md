
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3392.29 | 0.103613 | 5114.32ms | 699405 | 320 | 1.32815e+07 | 196624 | 0.0943871 | 1(Win) | true |
| Glaze | 2533.42 | 0.208535 | 6857.01ms | 699405 | 30 | 9.04317e+06 | 263282 | 0.0442802 | 2(Loss) | true |
| simdjson (ondemand) | 1629.49 | 0.0973309 | 6005.51ms | 767297 | 320 | 6.11325e+07 | 449066 | 0.410841 | 3(Loss) | true |
