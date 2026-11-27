
----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5176.85 | 0.0397574 | 813.382ms | 4857 | 4890 | 618.801 | 894.752 | 0.0689737 | 1.03815 | 4.7064 | 0.694256 | 0.000570214 | 1.62521e-05 | 5.47352e-06 | 1(Win) | true |
| simdjson (ondemand) | 4098.11 | 0.168732 | 843.306ms | 4857 | 40 | 145.487 | 1130.28 | 0.0758826 | 1.27895 | 5.38872 | 0.704344 | 0.00107577 | 2.05888e-05 | 5.14721e-06 | 2(Loss) | true |
