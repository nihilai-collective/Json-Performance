
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23034.9 | 0.227962 | 235.425ms | 56369 | 80 | 2264.24 | 2333.75 | 0.160428 | 0.106269 | 1(Win) | true |
| simdjson (stage-1) | 20058.8 | 0.167924 | 271.421ms | 56369 | 80 | 1620.25 | 2680 | 0.0931966 | 0.121393 | 2(Loss) | true |
