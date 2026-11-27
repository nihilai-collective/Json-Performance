
----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9841.49 | 0.259463 | 781.694ms | 4857 | 2560 | 3817.74 | 470.66 | 0.26529 | 0.560932 | 1.78011 | 0.271773 | 0.000264679 | 5.85495e-05 | 2.77467e-05 | 1(Win) | true |
| Glaze | 3126.49 | 0.132845 | 884.547ms | 4857 | 4890 | 18941.9 | 1481.53 | 0.101923 | 1.66637 | 4.16821 | 0.63496 | 0.000212751 | 6.48822e-05 | 2.33256e-05 | 2(Loss) | true |
