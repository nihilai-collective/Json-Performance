
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15615.3 | 0.0615287 | 349.899ms | 56369 | 40 | 179.471 | 3442.62 | 0.0627337 | 0.157308 | 1(Win) | true |
| simdjson (reflection) | 13465.5 | 0.0535788 | 403.444ms | 56369 | 40 | 183.013 | 3992.25 | 0.00125244 | 0.182628 | 2(Loss) | true |
| Glaze | 5255.41 | 0.145842 | 1026.67ms | 56369 | 4890 | 1.08828e+06 | 10229 | 0.109257 | 0.469837 | 3(Loss) | true |
