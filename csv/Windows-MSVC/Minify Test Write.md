
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3453.68 | 0.577252 | 6476.73ms | 466906 | 320 | 1.77246e+08 | 128928 | 0.00678627 | 0.716663 | 1(Win) | true |
| Glaze | 1755.22 | 0.141885 | 6558.55ms | 466906 | 320 | 4.14591e+07 | 253687 | 0.426051 | 1.41036 | 2(Loss) | true |
| simdjson (ondemand) | 1316.13 | 0.207894 | 8788.93ms | 466906 | 80 | 3.95764e+07 | 338322 | 0.0724686 | 1.88085 | 3(Loss) | true |
