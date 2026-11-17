
----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 201.724 | 0.631304 | 7498.47ms | 2090234 | 30 | 1.16755e+11 | 9.88184e+06 | 0.44647 | 12.2732 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 190.162 | 0.90635 | 7746.04ms | 2090234 | 40 | 3.61072e+11 | 1.04826e+07 | 4.32726 | 13.0194 | -(Loss) | false |
