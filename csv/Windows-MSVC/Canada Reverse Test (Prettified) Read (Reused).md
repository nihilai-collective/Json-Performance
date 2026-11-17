
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE DID NOT CONVERGE | 489.162 | 1.38709 | 7471.02ms | 5212421 | 30 | 5.96082e+11 | 1.01622e+07 | 2.65274 | 5.06132 | -(Tie) | false |
| simdjson (ondemand) STATISTICAL TIE | 476.291 | 0.343701 | 7835.82ms | 5212421 | 40 | 5.14704e+10 | 1.04368e+07 | 0.279761 | 5.19813 | 1(Tie) | true |
