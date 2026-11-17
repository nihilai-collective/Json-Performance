
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 8925.44 | 0.0804227 | 111.197ms | 9578 | 80 | 54.1924 | 1023.4 | 0.0415455 | 0.270156 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 8921.3 | 0.0878975 | 111.17ms | 9578 | 80 | 64.7943 | 1023.88 | 0.28001 | 0.270287 | 1(Tie) | true |
| Glaze | 3872.06 | 0.0363798 | 248.498ms | 9578 | 40 | 29.4609 | 2359.03 | 0.00883055 | 0.631601 | 3(Loss) | true |
