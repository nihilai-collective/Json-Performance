
----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12190.1 | 0.0427072 | 41.4245ms | 4857 | 1280 | 33.7079 | 379.979 | 0.182704 | 0.189479 | 1(Win) | true |
| Glaze | 3893.25 | 0.0817738 | 123.822ms | 4857 | 160 | 151.447 | 1189.75 | 0.00630424 | 0.621777 | 2(Loss) | true |
